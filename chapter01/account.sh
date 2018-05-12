#!/ usr/bin/bash

while read line; do
    name=`echo $line | sed -e "s/ .*$//"`
    useradd -m $name
    echo -e "$name\n$name\n" | sed "s/-e //" | passwd $name
    cp -f /etc/profile /home/$name/.profile
    chown $name.$name /home/$name/.profile
done
