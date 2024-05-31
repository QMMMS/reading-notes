import os
# 下载网络图片
import requests
# 正则表达式
import re


md_path = './qms_01_总线.md'
img_folder_path = './img/'

# 读取md文件
with open(md_path, 'r', encoding='utf-8') as f:
    md_content = f.read()

# 匹配图片链接
img_urls = re.findall(r'!\[.*?\]\((.*?)\)', md_content)

for(url) in img_urls:
    # 获取图片名称
    img_name = url.split('/')[-1]
    # 下载图片
    img = requests.get(url)
    # 保存图片
    with open(img_folder_path + img_name, 'wb') as f:
        f.write(img.content)
    # 替换md文件中的图片链接
    md_content = md_content.replace(url, img_folder_path + img_name)

# 保存md文件
with open(md_path, 'w', encoding='utf-8') as f:
    f.write(md_content)
    