Import("env")

import sys
import subprocess
subprocess.check_call([sys.executable, '-m', 'pip', 'install',
'gitpython'])

import git

print("Current CLI targets", COMMAND_LINE_TARGETS)
print("Current Build targets", BUILD_TARGETS)

git_version = "NOT IN GIT REPO"

try:
    repo = git.Repo(search_parent_directories=True)
    git_version = repo.head.object.hexsha
except:
    print("No git repo found")

file=open("./include/values.h","w")
file.write("#define GIT_COMMIT \"" + git_version + "\"")
file.close()