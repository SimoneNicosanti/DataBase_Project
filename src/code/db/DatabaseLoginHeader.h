#pragma once

#include <stdbool.h>
#include "../controller/LoginControllerHeader.h"
#include "DatabaseUtilsHeader.h"

Role attemptLogin(LoginCredentials *loginDredentialsPtr) ;

void switchRole(Role newRole) ;