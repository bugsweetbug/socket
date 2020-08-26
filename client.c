#include "sock_include.h"

int main()
{
	int cfd, ret, n;
	char buf[BUFSIZ];
	struct sockaddr_in serv_addr;
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
	ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret < 0)
		{
			perror("connect error");
			exit(1);
		}
	while (1)
		{
			bzero(buf,sizeof(buf));
			fgets(buf, sizeof(buf), stdin);
			n = write(cfd, buf, strlen(buf));

			read(cfd, buf, n);
			write(STDOUT_FILENO, buf, n);

			
		}
		close(cfd);
	return 0;
}
