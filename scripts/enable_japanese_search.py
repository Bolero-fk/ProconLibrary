"""
Just the Docsの検索機能で、日本語を検索できるようにするスクリプト。

本リポジトリで公開しているドキュメントでは、サイトテーマとして
Just the Docsを使用しており、その検索機能にはLunrが使用されています。
標準状態のLunrでは日本語を適切に検索できないため、検索インデックスの
初期化時に次のコードを追加します。

    this.use(lunr.multiLanguage('en', 'ja'));

書き換え対象は、Jekyllによるサイト生成後の次のファイルです。

    _site/assets/js/just-the-docs.js

以前はGitHub Actions内のsedコマンドで直接書き換えていましたが、
次の理由から専用のPythonスクリプトへ分離しています。

- Workflowの定義を読みやすくするため
- sedの複雑なクォートやエスケープを避けるため
- 書き換え対象が変化した場合に、処理を明示的に失敗させるため
- ローカル環境でも同じ処理を実行できるようにするため

GitHub Actionsでは生成されたファイルを通常ユーザーが変更できないため、
Workflowからはsudoを付けてこのスクリプトを実行します。

実行例:

    sudo python3 scripts/enable_japanese_search.py _site/assets/js/just-the-docs.js
"""

import sys
from pathlib import Path

# Just the Docsが検索インデックスを初期化している箇所。
# この文字列の直後へ、日本語検索を有効化するコードを追加します。
LUNR_INDEX_MARKER = "var index = lunr(function(){"

# 元の初期化処理と、追加する日本語検索の設定をまとめた置換後の文字列。
JAPANESE_SEARCH_INITIALIZER = f"{LUNR_INDEX_MARKER}\n" "        this.use(lunr.multiLanguage('en', 'ja'));"


def enable_japanese_search(file_path: Path) -> None:
    """
    Just the DocsのJavaScriptへ、日本語検索の設定を追加する。

    Args:
        file_path:
            書き換えるjust-the-docs.jsのパス。

    Raises:
        FileNotFoundError:
            指定されたファイルが存在しない場合。
        RuntimeError:
            書き換え対象が1箇所だけ存在しない場合。
    """

    if not file_path.is_file():
        raise FileNotFoundError(f"ファイルが見つかりません: {file_path}")

    source = file_path.read_text(encoding="utf-8")
    marker_count = source.count(LUNR_INDEX_MARKER)

    # 対象が0箇所の場合はJust the Docs側のコードが変わった可能性があります。
    # 複数箇所の場合は追加先を一意に決められないため、どちらも失敗させます。
    if marker_count != 1:
        raise RuntimeError(
            "Lunrの検索インデックス初期化処理が" f"1箇所だけ存在する想定ですが、{marker_count}箇所見つかりました。"
        )

    updated_source = source.replace(
        LUNR_INDEX_MARKER,
        JAPANESE_SEARCH_INITIALIZER,
        1,
    )

    file_path.write_text(updated_source, encoding="utf-8")


def main() -> None:
    """コマンドライン引数から対象ファイルを受け取り、書き換えを実行する。"""

    # sys.argvにはスクリプト名も含まれるため、
    # 対象ファイルを1個受け取った場合の要素数は2になります。
    if len(sys.argv) != 2:
        raise SystemExit("Usage: python3 enable_japanese_search.py " "<path-to-just-the-docs.js>")

    target_file = Path(sys.argv[1])
    enable_japanese_search(target_file)


if __name__ == "__main__":
    main()
