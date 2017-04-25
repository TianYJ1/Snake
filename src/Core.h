#pragma once
void initAddons();
void changeScene(int scene);
void Log_i(const char * tag, const char *str, ...);
void Log_e(const char * tag, const char *str, ...);
void initVars();
int openLevel(int num);
void setNewScreen();
void renderScreen();
void convertConstCopy(const char *source, char *toChr);
