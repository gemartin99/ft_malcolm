export DOCKER_HOST=unix:///var/run/docker.sock

sudo docker exec -it dest arping -c 1 192.168.0.2

#sudo ./ft_malcom 192.168.0.3 aa:bb:cc:dd:ee:ff 192.168.0.2 aa:aa:aa:aa:aa:aa