#if !defined(__INIT_H) 
#define __INIT_H 

#include "header.h"

Tblock GetBlock(int x, int y, size_t dx, size_t dy, size_t cond);
COORD GetPoint(int x, int y);

void InitblocksMainMenu(TblocksMainMenu* pblocks, TblocksMenu* p_allblocks);
void InitblocksCustomGame(TblocksCustomGame* pblocks, TblocksMenu* p_allblocks);
void InitblocksSimulation(TblocksSimulation* pblocks, TblocksMenu* p_allblocks);
void InitblocksSettings(TblocksSettings* pblocks, TblocksMenu* p_allblocks);
void InitblocksGameRule(TblocksGameRule* pblocks, TblocksMenu* p_allblocks);
void InitblocksMenu(TblocksMenu* pblocks, size_t baseX, size_t baseY);
void InitBlockGame(TblocksGame* pblocks, size_t baseX, size_t baseY);

#endif 