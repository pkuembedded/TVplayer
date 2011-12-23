#/bin/bash
echo "Waiting for converting..."
killall ffserver
ffserver -f /home/infinite/myffserver.conf &
ffmpeg -i /home/infinite/Project/Benchmark/480p.mov http://localhost:8090/feed1.ffm
echo "Server started"
