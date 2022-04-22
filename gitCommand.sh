##### Shell Script for Authomatic Commit #####
# @Param $* -> All strings after ./gitCommand.sh
 
git add . ;
git commit -m "$*" ;
git push origin main ;
printf "SimoneNicosanti\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" | ./gitCommand.sh
