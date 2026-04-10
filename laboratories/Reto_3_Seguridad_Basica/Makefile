APP=src/main.sh

all:
	chmod +x src/main.sh src/user/user.sh src/utils/validation.sh src/policy/policy.sh
	cp src/main.sh user_admin_app
	chmod +x user_admin_app

run:
	sudo ./src/main.sh help

clean:
	rm -f user_admin_app

docker-build:
	docker build -t reto3-user-admin .

docker-run:
	docker run --rm -it --name reto3-user-admin reto3-user-admin
