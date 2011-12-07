#include "audio.h"

void audio_callback(void *userdata, Uint8 *stream, int len) 
{
    Media *audio = (Media *)userdata;
    int len1, audio_size;
    double pts;
    while(len > 0) {
	if(audio->audio_buf_index >= audio->audio_buf_size) {
	    /* We have already sent all our data; get more */
	    audio_size = decode_audio(audio, audio->audio_buf, sizeof(audio->audio_buf), &pts);
	    if(audio_size < 0) {
		/* If error, output silence */
		audio->audio_buf_size = 1024;
		memset(audio->audio_buf, 0, audio->audio_buf_size);
	    } else {
		audio->audio_buf_size = audio_size;
	    }
	    audio->audio_buf_index = 0;
	}
	len1 = audio->audio_buf_size - audio->audio_buf_index;
	if(len1 > len)
	    len1 = len;
	memcpy(stream, (uint8_t *)audio->audio_buf + audio->audio_buf_index, len1);
	len -= len1;
	stream += len1;
	audio->audio_buf_index += len1;
    }
}

int find_audio_decoder(Media *audio)
{
    AVCodec *aCodec;
    SDL_AudioSpec wanted_spec, spec;
    wanted_spec.freq = audio->codec_ctx->sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = audio->codec_ctx->channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
    wanted_spec.callback = audio_callback;
    wanted_spec.userdata = audio;
    
    if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
      LOGV("SDL_OpenAudio : find_audio_decoder");
      return -1;
    }
    audio->audio_hw_buf_size = spec.size;

    aCodec = avcodec_find_decoder(audio->codec_ctx->codec_id);
    if(aCodec == NULL)
    {
	LOGV("Codec not found : find_audio_decoder");
	return 4;
    }
    if(avcodec_open(audio->codec_ctx, aCodec) < 0)
	return 5;

    audio->audio_buf_size = 0;
    audio->audio_buf_index = 0;
    memset(&audio->audio_pkt, 0, sizeof(audio->audio_pkt));
    SDL_PauseAudio(0);
    return 0;
}


int decode_audio(Media *audio, uint8_t *audio_buf, int buf_size, double *pts_ptr)
{
    int len1, data_size, n;
    AVPacket *pkt = &audio->audio_pkt;
    double pts;

    for(;;) {
	while(audio->audio_pkt_size > 0) {
	    data_size = buf_size;
	    len1 = avcodec_decode_audio3(audio->codec_ctx, 
					 (int16_t *)audio_buf, &data_size, pkt);
	    if(len1 < 0) {
		/* if error, skip frame */
		audio->audio_pkt_size = 0;
		break;
	    }
	    audio->audio_pkt_data += len1;
	    audio->audio_pkt_size -= len1;
	    if(data_size <= 0) {
		/* No data yet, get more frames */
		continue;
	    }
	    pts = audio->clk;
	    *pts_ptr = pts;
	    n = 2;//* audio->codec_ctx->channels;
	    audio->clk += (double)data_size /
		(double)(n * audio->codec_ctx->sample_rate);

	    /* We have data, return it and come back for more later */
	    return data_size;
	}
	if(pkt->data)
	    av_free_packet(pkt);
	/* next packet */
	if(get_from_queue(&audio->raw_data_buf, pkt) < 0) {
	    break;
	}
	audio->audio_pkt_data = pkt->data;
	audio->audio_pkt_size = pkt->size;
	/* if update, update the audio clock w/pts */
	if(pkt->pts != AV_NOPTS_VALUE) {
	    audio->clk = av_q2d(audio->codec_ctx->time_base)*pkt->pts;
	}
    }
}

void init_audio(Media *audio)
{
    memset(audio, 0, sizeof(Media));
    audio->media_type = AUDIO;
    audio->play_cond = SDL_CreateCond();    
    audio->play_mutex = SDL_CreateMutex();    
    audio->find_codec = find_audio_decoder;
    audio->get_info = get_av_info;
}
