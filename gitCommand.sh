##### Shell Script for Authomatic Commit #####
# @Param $* -> All strings after ./gitCommand.sh
 
git add . ;
git commit -m "$*" ;
git push https://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@github.com/SimoneNicosanti/DataBase_Project.git origin main ;
