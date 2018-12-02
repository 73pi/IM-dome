#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "all.h"

//宏：构建不同链表的节点类型
#define LinkConstruct(LinkName,dataType)\
typedef struct LinkName\
{\
	dataType data;\
	struct Linkname *next;\	
}Linkname,*p##Linkname;

LinkConstruct(UserLink, User)

typedef struct OnlineUser
{
	char name[MINSIZE];
	int fd;
}OnlineUser;

LinkConstruct(OnlineLink,OnlineUser);

typedef struct UnsendMsg
{
	char sender[MINSIZE];//发送者账号
	char receiver[MINSIZE];//接收者账号
	char msg[MEDIUMSIZE];//未发送的消息内容
}UnsendMsg;

LinkConstruct(Unsendkink,UnsendMsg);

typedef struct DownFile
{
	char fileName[MEDIUMSIZE];
	char time[MEDIUMSIZE];
}DownFile;

LinkConstruct(DownLink,DownFile)

//判断注册用户是否存在的类型
typedef enum ExistType
{
	ExistTypeyes,
	ExistTypeno
}ExistType;

//判断在线用户的存在类型
typedef enum OnlineType
{
	OnlineTypeyes,
	OnlineTypeno
}OnlineType;

//宏
#define USERFILENAME "/home/wu/1704/聊天室/registerUser.txt"
#define UNSENDMSGFILE "/home/wu/1704/聊天室/unsendMsg.txt"
#define SERVERFILE "/home/wu/1704/聊天室/"

//函数的声明
ExistType hasExistRegisterUser(User user);

void addRegisterUser(User data);
void creatDownList();

void creatOnlineUserList();
void readRegisterUserFromFlie();
void readUnsendMsgFromFile();
void outOnlineUserBySockfd(int fd);
pOnlineLink getOnlineUserNameBySockfd(int fd);
void addOnlineUser(OnlineUser data);
void changeOnlineSockfdByName(char *name,int currentfd);
int getSockfdByOnlineUserByName(char *name);
OnlineType hasOnlineUserByName(char *Name);
void deteleDownloadFile(char *fileName);
void addDownFile(DownFile data);
int isDownloadingFirstPacket(DownFile downFile);
pUserLink getUserData(User user);
void saveUnsendMsgToFile();
void addUnsendMsg(UnsendMsg data);
void changeUserPasswd(User newUser);
int checkNameAndPasswd(User user);
void saveRegisterUserToFile();

//变量的声明
extern pUserLink userHead;//注册链表的头

extern pOnlineLink onlineHead;//在线链表的头

extern pUnsendLink unsendHead;//未发送信息的链表头

extern pDownLink downHead;//正在下载的文件头

#endif /* LIST_H */