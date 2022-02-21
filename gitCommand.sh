##### Script Shell Per Commit Automatico #####
# @Param $0 : messaggio del commit

git add . ;
git commit -m "$1" ;
git push origin main ;
