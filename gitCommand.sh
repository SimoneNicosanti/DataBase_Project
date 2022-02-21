##### Script Shell Per Commit Automatico #####
# @Param $1 : messaggio del commit 

git add . ;
git commit -m "$1" ;
git push origin main ;
