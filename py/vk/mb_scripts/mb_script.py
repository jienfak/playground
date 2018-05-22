#!/usr/bin/python3
token_group = '62f8334bbfcb80f730c479a1675a69bbf7140893f7318382d8af68ea37437573b69cbd1995ce98fc97f77';
token_user  = '69a4858f0529f1a0070b00cf9e03a12c127fe7031efe5b7f6f6e7b41571a5288e582be5fbf378abae9503';

import vk;

session_user = vk.Session(access_token=token_user);
api_user = vk.API(session_user);

session_group = vk.Session(access_token=token_group);
api_group = vk.API(session_group);

print(
        api_user.groups.getByld(
            )
        );
exit();
