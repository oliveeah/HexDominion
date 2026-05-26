# Weekly Progress Summary

This document tracks the weekly progress of the Production Project 2 (Unreal Engine 5.6 Board Game).

**First Commit Date:** November 19, 2025

---

## Week Commencing: November 17, 2025

*First commit made on November 19, 2025*

### Summary
Initial project setup and foundation work. The first commit established the core project structure.

### Completed Work
- **Project Initialization**: Created Unreal Engine 5.6 project with Third Person template
- **C++ Script Structure**: Set up folder structure for C++ scripts
- **Map Generation System**: Finalized initial map generation using FastNoiseLite for procedural terrain
- **Tile System Foundation**: Created tile-based biome system including:
  - Base tile blueprint (BP_BG_Tile)
  - Multiple biome types: Forest, Grassland, Hill, Mountain, Sandy, Stone, Water
  - Tile variations for each biome (houses, farms, villages, castles, etc.)
- **Character System**: Set up ProductionProjCurrCharacter with camera controls
- **NPC Base Class**: Created NPC_BaseClass with interaction interface (testInterface)
- **Card System**: Implemented card hand widget with data assets (CardData_1 through CardData_20)
- **Animated Animals**: Added animated deer and fish blueprints
- **Player System**: Created board game player pawn and player widget
- **Token System**: Implemented board game token blueprint
- **Tile Spawner**: Created BP_BG_TileSpawner for procedural tile placement

### Commits
- `952e99b` - created folders for c++ scripts and finalised map generation for now

### Errors Encountered
- No significant errors reported during initial project setup

---

## Week Commencing: November 24, 2025

### Summary
Current active development week. Documentation and planning updates.

### Completed Work
- **Documentation**: Initial project planning and documentation setup

### Commits
- `c555c4c` - Initial plan

### Errors Encountered
- No significant errors reported during this week

### In Progress
- Continued development of board game mechanics
- Refinement of tile generation system
- Further NPC and interaction system development

---

## Week Commencing: December 1, 2025

### Summary
Development continuation and documentation updates.

### Completed Work
- **Documentation**: Added weekly progress tracking with errors encountered sections

### Commits
- *(Pending commits this week)*

### Errors Encountered
- No significant errors reported during this week

### In Progress
- Ongoing game development
- Feature refinements

---

## Project Overview

### Core Systems
1. **Procedural Map Generation**: Uses FastNoiseLite for noise-based terrain generation with multiple biome types
2. **Tile-Based World**: Modular tile system with various biome variants
3. **Card System**: Data-driven card system with hand management
4. **Character Controller**: Third-person camera and movement system
5. **NPC Interaction**: Interface-based interaction system for NPCs

### Technology Stack
- **Engine**: Unreal Engine 5.6
- **Language**: C++ with Blueprints
- **Plugins**: StateTree, GameplayStateTree, ModelingToolsEditorMode, Text3D

---

*Last Updated: December 7, 2025*
