# telnet 与 POP3 实验

POP3协议，用于接收邮件，同样可以使用`telnet`命令手动模拟

**用户端需要手动键入的信息有：**

```
user 账号
pass 密码
list			#列出所有邮件
retr 数字			#查看数字标识的邮件
dele 数字			#删除数字标识的邮件
quit			#退出
```

**全部实验过程：**

```
[user1@qmmms ~]$ telnet mail.dlut.edu.cn 110
Trying 202.118.66.82...
Connected to mail.dlut.edu.cn.
Escape character is '^]'.
+OK Welcome to coremail Mail Pop3 Server (dlut.edu.cns[627644c969381353b51c9657b72568a4s])
user xxxxxxxxxx@mail.dlut.edu.cn
+OK core mail
pass xxxxxxxxxx
+OK 4 message(s) [1151199 byte(s)]
list
+OK 4 1151199
1 398270
2 741119
3 1682
4 10128
.
retr 3
+OK 1682 octets
Received: from xxxxxxxxx (unknown [xxxxxxxxx])
        by mx1 (Coremail) with SMTP id UEJ2ygBnb+8toTZjKwx_CA--.36240S2;
        Fri, 30 Sep 2022 15:56:40 +0800 (CST)
hello from linux
X-CM-TRANSID:UEJ2ygBnb+8toTZjKwx_CA--.36240S2
Message-Id:<6336A15F.04A767.07381@dlut.edu.cn>
Authentication-Results: mx1; spf=none smtp.mail=xxx@xxxxxx;
X-Coremail-Antispam: 1UD129KBjDUn29KB7ZKAUJUUUUU529EdanIXcx71UUUUU7v73
        VFW2AGmfu7jjvjm3AaLaJ3UjIYCTnIWjp_UUUrS7k0a2IF6F4UM7kC6x804xWl14x267AK
        xVWUJVW8JwAFIxvE14AKwVWUJVWUGwA2ocxC64kIII0Yj41l84x0c7CEw4AK67xGY2AK02
        1l84ACjcxK6xIIjxv20xvE14v26r1j6r1xM28EF7xvwVC0I7IYx2IY6xkF7I0E14v26r1j
        6r4UM28EF7xvwVC2z280aVAFwI0_Jr0_Gr1l84ACjcxK6I8E87Iv6xkF7I0E14v26r1j6r
        4UM2vYz4IE57IF64kE628EF7xvwwAS0I0E0xvYzxvE52x082IY62kv0487M2AExVAIFx02
        aVAFz4v204v7Mc8Ir4CE8sxKj4xv1VAv77x28xyl52xGzVA2a4k0FcxF6cIjj282cryl5I
        8CrVACY4xI64kE6c02F40Ex7xfMcIj64x0Y40En7xvr7AKxVWUJVW8JwAv7VC0I7IYx2IY
        67AKxVWUtVWrXwAv7VC2z280aVAFwI0_Jr0_Gr1lOx8S6xCaFVCjc4AY6r1j6r4UM4x0Y4
        8IcVAKI48JM4x0aVACjI8F5VA0II8E6IAqYI8I648v4I1lw4AK0VCY07AIYIkI8VC2zVAC
        3wAKzVAC0xCFj2AI6cx7M4kE6I8I3I0E14AKx2xKxVC2ax8xMx02cVCv0xWlc7CjxVAKzI
        0EY4vE52x082I5MxkI7II2jI8vz4vEwIxGrwCYIxAIcVC0I7IYx2IY67AKxVWUJVWUCwCY
        IxAIcVC0I7IYx2IY6xkF7I0E14v26r1j6r4UMxvI42IY6I8E87Iv67AKxVWUJVW8JwCYIx
        AIcVC2z280aVCY1x0267AKxVWUJVW8JwCF04k20xvY0x0EwIxGrwCF04k20xvEw4C26cxK
        6c8Ij28IcwCFw20E84ACjcxK64kEx2IqYxC7MxCjnVAKz4kxMxC20s026xCaFVCjc4AY6r
        1j6r4UMI8I3I0E5I8CrVAFwI0_Jr0_Jr4lx2IqxVCjr7xvwVAFwI0_Jr0_Jr4lx4CE17CE
        b7AF67AKxVWUJVWUXwCI42IY6xAIw20EY4v20xvaj40_Zr0_Wr1UYxBIdaVFxhVjvjDU0x
        ZFpf9x07b6AwxUUUUU=
Date: Fri, 30 Sep 2022 15:57:19 +0800 (CST)
From: xxx@xxxxxx

.
quit
+OK core mail
Connection closed by foreign host.
```

