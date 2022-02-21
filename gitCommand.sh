##### Shell Script for Authomatic Commit #####
# @Param $1 -> Commit Message

git add . ;
git commit -m "$*" ;
git push origin main ;
