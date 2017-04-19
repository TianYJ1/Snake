#pragma once
void initAddons(); 
void changeScene(int scene);
void Log_i(char * tag, const char *str, ...);
void Log_e(char * tag, const char *str, ...);
void initVars();
int openLevel(int num);
void setNewScreen();
void renderScreen();