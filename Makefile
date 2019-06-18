all:
	@gcc scron.c -O3 -pthread -o scrond

test:

clean:
	rm -f scrond

install:all
	@cp -f scrond /usr/bin/scrond
	@cp -f scrond.service /etc/systemd/system/scrond.service
	@systemctl enable --now scrond
