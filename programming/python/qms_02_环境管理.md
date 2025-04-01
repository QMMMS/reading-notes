# 环境管理

## pyenv

[pyenv for Windows](https://github.com/pyenv-win/pyenv-win)，安装步骤见 README

命令：

- 版本：`pyenv --version`

- 当前安装的所有版本：`pyenv versions`

- 支持的 Python 版本列表：`pyenv install -l`

- 要筛选列表：`pyenv install -l | findstr 3.8`

- 安装支持的版本：`pyenv install <version>`

- 删除版本：`pyenv uninstall <version>`

- 删除版本：`pyenv uninstall <version> `

- 设置为全局版本：`pyenv global <version>`

- 检查正在使用的 Python 版本及其路径：`pyenv version`

- 检查 Python 是否正常工作：`python -c "import sys; print(sys.executable)"`

## conda
