#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/type.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>

#define CHECKERROR(fd,error) \
if (fd < 0)\
{\
	perror(error);\
	exit(0);\
}

typedef enum MsgType
{
	//注册
	MsgTypeRegisterRequest,
	MsgTypeRegisterRespondFaild,
	MsgTypeRegisterRespondSuccess,

	//忘记密码
	MsgTypeForgetPassewdRequest,
	MsgTypeForgetPassewdRespondFailed,
	MsgTypeForgetPassewdRespondSuccess,

	//登录
	MsgTypeLoginRequest,
	MsgTypeLoginRespondFailed,
	MsgTypeLoginRespondSuccess，

	//修改密码
	MsgTypeChangePasswdRequest,
	MsgTypeChangePasswdRespondfailed,
	MsgTypeChangePasswdRespondSuccess，

	//聊天
	MsgTypeChatRequest,
	MsgTypeChatRespondFailed,
	MsgTypeChatRespondSuccess,

	//获取文件列表
	MsgTypeGetFileListRequest,
	MsgTypeGetFileListRespondFailed,
	MsgTypeGetFileListRespondSucess,

	//下载文件
	MsgTypeDownloadFileRequest,
	MsgTypeDownloadFileRespondFailed,
	MsgTypeDownloadFileRespondSuccess,

	//重命名文件
	MsgTypeRenameFailedRequest,
	MsgTypeRenameFailedRespondFailed,
	MsgTypeRenameFailedRespondSuccess.

	//删除文件
	MsgTypeDeleteFileRequest,
	MsgTypeDeleteFileRespondFailed,
	MsgTypeDeleteFileRespondSuccess,

	MsgTypeMax = 0x0fffffff
}MsgType;

#define MINSIZE 20
#define MAXSIZE 400
#define MEDIUMSIZE MAXSIZE/2
#define MAXIOSIZE 2048 //2k

typedef struct User
{
	MsgType msgType;//消息类型
	char name[MINSIZE];//名字
	char passwd[MINSIZE];//密码
	char attachMsg[MAXSIZE];//附件信息
}User;

typedef struct MsgContent
{
	MsgType msgType;//消息类型
	char attachMsg[MAXSIZE];//附件信息
}MsgContent;

typedef struct File
{
	char fileName[MEDIUMSIZE];//文件名
	char time[MEDIUMSIZE];//文件时间
	long long offset;//文件偏移量
	long long left;//文件剩余大小
	int textSize;//文件内容的实际大小
	char text[MAXIOSIZE];//文件内容
}File;

/* 线程传参，由于线程函数只能传递一个参数，想要传多个参数，
就必须定义一个结构体 */
typedef struct ThreadArgs
{
	char fileName[MEDIUMSIZE];
	int fd;
}ThreedArgs;

#endif /* ALL_H */