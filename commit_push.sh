##### Shell Script for Authomatic Commit #####
# @Param $* -> All strings after ./gitCommand.sh

username="SimoneNicosanti" ;
token="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" ;
repo_name="DataBase_Project" ;
 
git add . ;
echo "$0" >> .gitignore ;
git commit -m "$*" ;
git push https://$username:$token@github.com/$username/$repo_name.git ;
