
server = server
client = client

all:$(server) $(client)

$(server):
	gcc -g  -o server  ../../../zmalloc.c ../../../adlist.c  ../mp_channel.c mp_channel_server.c
$(client):
	gcc -g  -o client  ../../../zmalloc.c ../../../adlist.c  ../mp_channel.c mp_channel_client.c


clean:
	rm -rf $(server) $(client)
