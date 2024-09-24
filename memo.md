# Dropbox トークンの取得について
基本的には ```oj d --system https://atcoder.jp/contests/agc001/tasks/agc001_a``` を実行して表示される出力に従い、ACCESS_TOKENを取得すればよい。  
ただし、誤ったURLが出力されることがあるので注意が必要。  
以下が正しい実行手順  
1. Open the following URL in your browser:
    https://www.dropbox.com/oauth2/authorize?client_id=c38wlsosanujy5z&response_type=code
2. Authorize the app and take the access code.
3. Run the following command with replacing the ```${YOUR_ACCESS_CODE}```:  
   ```$ curl https://api.dropbox.com/oauth2/token --user c38wlsosanujy5z:qgsndi0xoerw4j1 --data grant_type=authorization_code --data code=${YOUR_ACCESS_CODE}```
4. Get the access token from the JSON. It is in the "access_token" field.
5. Use the access token. For example:  
    ```$ oj download https://atcoder.jp/contests/agc001/tasks/agc001_a --system --dropbox-token=${YOUR_ACCESS_TOKEN}```

参考 https://github.com/online-judge-tools/oj/pull/914/commits/31cb8040f16107111468067bacb5d7450714bcbe

# Dropbox トークンの自動更新について
標準のアクセストークンの有効期限は4時間と非常に短いため、毎回更新が必要。  
リフレッシュトークンを使用することでアクセストークンの自動取得・更新が可能。  
## リフレッシュトークンの取得
基本的には[この記事](https://zenn.dev/yakumo/articles/75d3df651d0609)に従い、App key、App Secret、リフレッシュトークンを取得するが、最新の仕様変更により一部手順を変更する必要がある。
1. アプリケーションの設定画面の「Permission」タブで、```account_info.read```, ```files.metadata.read```, ```files.content.read```, ```sharing.read```の権限を有効にする。  
2. アクセスコードを取得する際は、以下のURL（```$APP_KEY```を実際のApp keyに置き換えたもの）を使用する。  
```https://www.dropbox.com/oauth2/authorize?client_id=$APP_KEY&response_type=code&token_access_type=offline&scope=account_info.read files.content.read files.metadata.read sharing.read```
## リフレッシュトークンの使用
GitHub ActionsのWorkflow内でジョブ間でトークンをやり取りする際、トークンの情報がログなどから漏洩しないように暗号化して取り扱います。  
1. 手元のコンソールで```openssl rand -base64 32```を実行し、暗号化に使用する秘密鍵を生成。  
2. 生成したApp key、App Secret、リフレッシュトークン、秘密鍵をGitHubのRepository Settings内の「Security > Secrets and variables > Actions」からそれぞれ以下のように登録します。
    - ```DROPBOX_APP_KEY```
    - ```DROPBOX_APP_SECRET```
    - ```DROPBOX_REFRESH_TOKEN```
    - ```AES256_KEY```
3. 以下のコミットを参考に```verify.yml```を編集する。  
- https://github.com/Bolero-fk/ProconLibrary/commit/d0b087d3d12deade217e37102648df1b8d872d85

参考 https://github.com/competitive-verifier/competitive-verifier/issues/95  
