# Level 02

- Once logged in, and check the file in home dir., the `level02.pcap` file is located

```
ssh level02@localhost -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          localhost 10.110.0.2
level02@localhost's password:
level02@SnowCrash:~$ ls
level02.pcap
level02@SnowCrash:~$
```

## What is pcap?
- `pcap` extension is a file that contains information of packet trasfer, that can be opened by [WireShark](https://www.wireshark.org/)
	- furthermore, check [here](https://www.comparitech.com/net-admin/pcap-guide/)

## SCP

- copy `level02.pcap` file to somewhere where `WireShark` is installed by using:

```
???$ scp -P 4242 level02@localhost:/home/user/level02/level02.pcap .
...
level02@1localhost's password:
???$ cat level02.pcap
cat: level02.pcap: Permission denied
```

- change permission of `level02.pcap` to read the file

```
???$ chmod +r level02.pcap
???$ cat level02.pcap
...
```

## decrypt the packets

```
???$ tshark -Tfields -e data -r level02.pcap | tr -d '\n' > data
???$ cat data
fffd25fffc25fffb26fffd18fffd20fffd23fffd27fffd24fffe26fffb18fffb20fffb23fffb27fffc24fffa2001fff0fffa2301fff0fffa2701fff0fffa1801fff0fffa200033383430302c3338343030fff0fffa2300536f646143616e3a30fff0fffa270000444953504c415901536f646143616e3a30fff0fffa1800787465726dfff0fffb03fffd01fffd22fffd1ffffb05fffd21fffd03fffc01fffb22fffa220301000003620304020f05000007621c08020409421a0a027f0b02150f02111002131102ffff1202fffffff0fffb1ffffa1f00b10031fff0fffd05fffb21fffa220103fff0fffa220107fff0fffa2103fff0fffb01fffd00fffe22fffd01fffb00fffc22fffa220303e20304820f07e21c08820409c21a0a827f0b82150f82111082131182ffff1282fffffff00d0a4c696e757820322e362e33382d382d67656e657269632d70616520283a3a666666663a31302e312e312e322920287074732f3130290d0a0a010077777762756773206c6f67696e3a206c006c6500657600766500656c006c5800580d01000d0a50617373776f72643a2066745f77616e64727f7f7f4e4452656c7f4c304c0d000d0a01000d0a4c6f67696e20696e636f72726563740d0a77777762756773206c6f67696e3a20
```

```
???$ cat data| xxd -r -p
��%��%��&���� ��#��'��$��&���� ��#��'��$�� ����#����'�������� 38400,38400����#SodaCan:0����'DISPLAYSodaCan:0����xterm��������"������!������"��"bb     B

 �����������1������!��"����"����!��������"������"��"���	�
�
  �����������
Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)

wwwbugs login: lleevveellXX
Password: ft_wandrNDRelL0L

Login incorrect
wwwbugs login:
```
- seems password is `ft_wandrNDRelL0L', but for a closer look,

```
???$ cat data | xxd -r -p | cat -e
��%��%��&��^X�� ��#��'��$��&��^X�� ��#��'��$�� ^A����#^A����'^A����^X^A���� ^@38400,38400����#^@SodaCan:0����'^@^@DISPLAY^ASodaCan:0����^X^@xterm����^C��^A��"��^_��^E��!��^C��^A��"��"^C^A^@^@^Cb^C^D^B^O^E^@^@^Gb^\^H^B^D	B^Z$
^B^?^K^B^U^O^B^Q^P^B^S^Q^B��^R^B������^_��^_^@�^@1����^E��!��"^A^C����"^A^G����!^C����^A��^@��"��^A��^@��"��"^C^C�^C^DM-^B^O^G�^\^HM-^B^D	�^Z$
M-^B^?^KM-^B^U^OM-^B^Q^PM-^B^S^QM-^B��^RM-^B����^M$
Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)^M$
$
^A^@wwwbugs login: l^@le^@ev^@ve^@el^@lX^@X^M^A^@^M$
Password: ft_wandr^?^?^?NDRel^?L0L^M^@^M$
^A^@^M$
Login incorrect^M$
wwwbugs login: %
```
the `^?` is interpreted as `null`


- check password with this code `ft_wandrNDRelL0L` for `flag02`
