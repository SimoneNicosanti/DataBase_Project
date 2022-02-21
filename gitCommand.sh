##### Shell Script for Authomatic Commit #####
# @Param $* -> All strings after ./gitCommand.sh

git add . ;
git commit -m "$*" ;
git push origin main ;
