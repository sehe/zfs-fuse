#!/bin/bash
#set -o xtrace

export BASENAME=dorky
# in MB, +_1:
export NUMDEVS=8
export DEVBLOCKUNIT=1M
export DEVCAPACITY=10240
export DEVPREALLOC=1
export POOLTYPE=raidz2
export OPTS="-O compression=on"

# derived vars
export blockdir=/tmp/${BASENAME}_blk
if [[ $DEVPREALLOC -le 0 ]]; then export DEVPREALLOC=1; fi
if [[ $DEVPREALLOC -gt $DEVCAPACITY ]]; then export DEVPREALLOC="$DEVCAPACITY"; fi

# restart zfs-fuse
zpool destroy "$BASENAME"
killall zfs-fuse
(sleep 0.5; killall -9 zfs-fuse; rm -fv /etc/zfs/zpool.cache; zfs-fuse; sleep 1)&

# mount block loopfile backing on tmpfs
if [[ 0 -eq $((for escaped_fs in $(cut -d\  -f2 /proc/mounts); do /bin/echo -e "$escaped_fs"; done) | grep "^$blockdir" | wc -l) ]]; then
	echo "mounting $blockdir..."
	mkdir -pv "$blockdir"
	mount -t tmpfs none "$blockdir"
else
	echo "$blockdir already mounted"
fi

# create backing files
for a in $(seq 1 $NUMDEVS); do dd if=/dev/zero bs=$DEVBLOCKUNIT seek=$(($DEVCAPACITY-$DEVPREALLOC)) count=$DEVPREALLOC of="$blockdir/z$a" 2> /dev/null; done&
wait # apparently there can be races with zfs-fuse... I thought removing zpool.cache would prevent this...

while [[ ! -f /var/lock/zfs/zfs_lock || ! -S /var/run/zfs/zfs_socket ]]; do
	sleep 0.5
	echo waiting for zfs-fuse...
done

# create pool and list status
zpool create $OPTS -O mountpoint="/tmp/$BASENAME" "$BASENAME" $POOLTYPE "$blockdir"/z*
zpool status -v
zfs list

# zpool destroy "$BASENAME" && killall zfs-fuse
