# dropbox tokenの取得について
基本は```oj d --system https://atcoder.jp/contests/agc001/tasks/agc001_a```を実行して出てくる出力に沿ってACCESS_TOKENを取得すればいいが、ojのverが古いと間違ったURLで出力される。
以下が正しい実行手順
https://github.com/online-judge-tools/oj/pull/914/commits/31cb8040f16107111468067bacb5d7450714bcbe
1. Open the following URL in your browser:
    https://www.dropbox.com/oauth2/authorize?client_id=c38wlsosanujy5z&response_type=code
    2. Authorize the app and take the access code.
    3. Run the following command with replacing the ```${YOUR_ACCESS_CODE}```:
        ```$ curl https://api.dropbox.com/oauth2/token --user c38wlsosanujy5z:qgsndi0xoerw4j1 --data grant_type=authorization_code --data code=${YOUR_ACCESS_CODE}```
    4. Get the access token from the JSON. It is in the "access_token" field.
    5. Use the access token. For example:
        ```$ oj download https://atcoder.jp/contests/agc001/tasks/agc001_a --system --dropbox-token=${YOUR_ACCESS_TOKEN}```
