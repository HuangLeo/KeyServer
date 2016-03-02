#!/bin/sh
#get local IP address
IP=`ifconfig eth0 | grep "inet addr:" | awk '{print $2}' | awk -F : '{print $2}'`
ipsec pki --gen --outform pem > cakey.pem
ipsec pki --self --in cakey.pem --dn "C=CH, O=strongSwan, CN=$IP" --ca --outform pem > cacert.pem

ipsec pki --gen --outform pem > serverkey.pem
ipsec pki --pub --in serverkey.pem | ipsec pki --issue --cacert cacert.pem --cakey cakey.pem --dn "C=CH, O=strongSwan, CN=$IP" --san="$IP" --flag serverAuth --outform pem >servercert.pem

ipsec pki --gen --outform pem > clientkey.pem
ipsec pki --pub --in clientkey.pem | ipsec pki --issue --cacert cacert.pem  --cakey cakey.pem  --dn "C=CH, O=strongSwan, CN=client" --outform pem > clientcert.pem

cp -r cacert.pem /etc/ipsec.d/cacerts/
cp -r servercert.pem /etc/ipsec.d/certs/
cp -r serverkey.pem /etc/ipsec.d/private/
cp -r clientcert.pem /etc/ipsec.d/certs/
cp -r clientkey.pem /etc/ipsec.d/private/

cp -r ipsec.conf /etc 
cp -r ipsec.secrets /etc 
cp -r strongswan.conf /etc

iptables -t nat -A POSTROUTING -s 192.168.0.0/16 -o eth0 -m policy --dir out --pol ipsec -j ACCEPT
iptables -t nat -A POSTROUTING -s 192.168.0.0/16 -o eth0 -j MASQUERADE
sysctl -w net.ipv4.ip_forward=1
echo 1 > /proc/sys/net/ipv4/ip_forward
iptables -t nat -A POSTROUTING -o eth0 ! -p esp -j SNAT --to-source "$IP"

#cd /work/upgrade/new/patch/config1/
#sh ip.sh
#sudo ipsec start
