#include "all.h"
#include "list.h"
#include "tool.h"

void handleRegisterRequest(int fd, User user)
{
	/*
     0>该user的信息是否已经被注册过
     1>将注册的用户保存到链表里面
     2>还需要将信息保存到文件里面，在程序一启动的时候就读取信息加载到链表
     */
	MsgContent msgContent;
	memset(msgContent, 0, sizeof(msgContent));
	if (hasExistRegisterUser(user) == ExistTypeYes)
	{
		//来到这说明姓名已经被注册过
        //将注册的反馈发送给客户端
        msgContent.msgType = MsgTypeRegisterRespondFaild;
        strcpy(msgContent.attachMsg, "用户名已存在");
	}
	else
	{
		addRegisterUser(user);
		saveRegisterUserToFile();
		MsgContent.msgType = MsgTypeRegisterRespondSuccess;
		strcpy(msgContent.attachMsg, "注册成功");
	}
	write(fd, &msgContent, sizeof(msgContent));
}
void handleForgetPasswdRequest(int fd, User user)
{
	pUserLink p = getUserData(user);
	MsgContent msgContent;
	if (NULL == p)
	{
		msgContent.msgType = MsgTypeForgetPasswdRespondFaild;
		strcpy(msgContent.attachMsg, "账号不存在");
	}
	else
	{
		msgContent.msgType = MsgTypeForgetPasswdRespondSuccess;
		//发送密保问题
		strcpy(msgContent.attachMsg, p->data/attachMsg);
	}
	//将忘记密码的反馈信息，发送给客户端
	write(fd, &msgContent, sizeof(msgContent));
	memset(msgContent, 0, sizeof(msgContent));
	read(fd, &msgContent,sizeof(msgContent));
	if (0 == strcmp(msgContent.attachMsg, p->data.attachMsg+MEDIUMZIZE))
	{
		msgContent.msgType = MsgTypeForgetPasswdRespondSuccess;
		strcpy(msgContent.attachMsg, p->data.passwd);
	}
	else
	{
		msgContent.msgType = MsgTypeForgetPasswdRespondFaild;
		strcpy(msgContent.attachMsg, "密保答案错误");
	}
	write(fd, &msgContent, sizeof(msgContent));
}
/*处理客户端的修改密码请求*/

