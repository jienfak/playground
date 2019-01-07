#!/usr/bin/python3
token_group = 'token';
token_user  = 'token';

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
