all:
	@gcc scron.c -O3 -pthread -o scron

test:

install:all
	@cp -f scron /usr/bin/scron
	@cp -f scron.service /etc/systemd/system/scron.service
	@systemctl enable --now scron
