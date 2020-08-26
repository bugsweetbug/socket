#include "sock_include.h"
int main()
{
	int lfd,ret,cfd,n;
	socklen_t clie_addr_len;
	char buf[BUFSIZ],clie_buf[BUFSIZ];
	int dst;
	struct sockaddr_in serv_addr, clie_addr;
	lfd = socket(AF_INET,SOCK_STREAM, 0);
	if(lfd < 0)
		{
			perror("socket error");
			exit(1);
		}
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, SERV_IP, &dst);
	serv_addr.sin_addr.s_addr = dst;
	ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret < 0)
		{
			perror("bind error");
			exit(1);
		}
	ret = listen(lfd, 128);
	if(ret < 0)
		{
			perror("listen error");
			exit(1);
		}
	clie_addr_len = sizeof(clie_addr);
	cfd = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
	printf("client IP:%s, client port:%d\n",inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr,
											clie_buf, sizeof(clie_buf)),
											clie_addr.sin_port);
	while(1)
		{
			n = read(cfd, buf, sizeof(buf));
			for(int i = 0; i < n; i++)
				{
					buf[i] = toupper(buf[i]);  //模拟数据CS交互，client发一个小写，server转成大写
				}
			write(cfd, buf, n);
		}
	close(lfd);
	close(cfd);
	return 0;
}