
combiner = combiner
primary = primary
worker = worker

all:$(combiner) $(primary) $(worker)

$(combiner):
	gcc -g  -o combiner  ../../../zmalloc.c ../../../adlist.c  ../mp_channel.c combiner.c
$(primary):
	gcc -g  -o primary  ../../../zmalloc.c ../../../adlist.c  ../mp_channel.c primary.c
$(worker):
	gcc -g  -o worker  ../../../zmalloc.c ../../../adlist.c  ../mp_channel.c worker.c



clean:
	rm -rf $(combiner) $(primary) $(worker)
