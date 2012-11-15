#include "Revelation.h"
#include "Config.h"
#include "Game.h"

bool CRevelation::m_LogInitialized = false;

void CRevelation::Log(string text) {
  if(!m_LogInitialized) {
    m_LogFile = GetLogPath();
    m_LogInitialized = true;
    Log("[Revelation] Starting up.");
  }

  if(!m_LogFile.empty()) {
    ofstream Log;
    Log.open(m_LogFile.c_str(), ios::app);

    if(!Log.fail()) {
      Log << text << endl;
      Log.close();
    }
  }
}

CRevelation::CRevelation(HMODULE hModule) {
  m_Game = new CGame(hModule);

  if(!m_Game)
    Log("[Revelation] Failed to create CGame instance!");
}

CRevelation::~CRevelation() {
  Log("[Revelation] Shutting down.");

  delete m_Game;
  m_Game = NULL;
}

string CRevelation::GetLogPath() {
  char g_szLocalPath[MAX_PATH] = { NULL };
  GetModuleFileName(GetModuleHandle(0), g_szLocalPath, MAX_PATH);
  PathRemoveFileSpecA(g_szLocalPath);
  strcat(g_szLocalPath, "\\");

  CConfig cfg;
  string config_path = g_szLocalPath + string("revelation.cfg");

  cfg.Read(config_path);
  return g_szLocalPath + cfg.GetString("revelation_log", "revelation.txt");
}

string CRevelation::m_LogFile = CRevelation::GetLogPath();