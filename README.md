# Production Project 2

An Unreal Engine C++ game project featuring procedural tile generation and hexagonal grid-based gameplay.

## 📖 Documentation

This project now includes comprehensive algorithm documentation with visual Mermaid diagrams!

### Quick Access to Documentation

#### 🚀 Start Here
**[Main Documentation Guide](docs/README.md)** - Learn about the documentation system, Mermaid diagram types, and how to create algorithm documentation.

#### 📝 For Contributors
**[Algorithm Template](docs/algorithms/README.md)** - Copy this template to document new algorithms. Includes examples of all Mermaid diagram types:
- Flowcharts (algorithm flow)
- Sequence Diagrams (component interactions)
- State Diagrams (algorithm states)
- Class Diagrams (object structure)
- Graphs (data structures)

#### 🎯 Example Documentation
**[Tile Spawning Algorithm](docs/algorithms/TileSpawning.md)** - Complete example showing how to document an algorithm with:
- Time/Space complexity analysis
- 5 different Mermaid diagrams
- Detailed pseudocode
- Edge cases and usage examples

### What's Included

```
docs/
├── README.md                      # Documentation guide & Mermaid overview
└── algorithms/
    ├── README.md                  # Template with all diagram examples
    └── TileSpawning.md           # Example: Tile spawning algorithm
```

### How to View the Documentation

#### On GitHub (Recommended)
1. Navigate to the [`docs/`](docs/) folder
2. Click on any `.md` file to view it
3. Mermaid diagrams render automatically - no plugins needed!

#### Locally
1. Clone this repository
2. Open markdown files in VS Code with "Markdown Preview Mermaid Support" extension
3. Or view in any markdown viewer that supports Mermaid

#### Interactive Editing
- Use [Mermaid Live Editor](https://mermaid.live) to create/edit diagrams
- Copy the code and paste into documentation

## 🎮 Project Overview

This is an Unreal Engine project with C++ components including:

### Key Components
- **Tile Spawning System** - Procedural hexagonal grid generation using Perlin noise
- **Game Mode & Player Systems** - Character controllers and game mode logic
- **Animation System** - Capture actors and animation handling
- **Input System** - Mouse interaction and player controls

### Technologies
- **Unreal Engine** - Game engine
- **C++** - Core gameplay logic
- **FastNoiseLite** - Procedural noise generation
- **Hexagonal Grids** - Grid-based tile system

## 🛠️ Development

### Project Structure
```
ProductionProjCurr/
├── Source/                    # C++ source code
│   └── ProductionProjCurr/
│       ├── Public/           # Header files
│       └── Private/          # Implementation files
├── Content/                  # Unreal assets
├── Config/                   # Configuration files
└── Binaries/                # Compiled binaries
```

### Key Algorithms Documented
- **[Tile Spawning](docs/algorithms/TileSpawning.md)** - O(n×m) procedural grid generation with biome distribution

## 📚 Additional Resources

- [Official Mermaid Documentation](https://mermaid.js.org/)
- [Mermaid Live Editor](https://mermaid.live)
- [Hexagonal Grids Guide](https://www.redblobgames.com/grids/hexagons/)
- [Unreal Engine Documentation](https://docs.unrealengine.com/)

## 🤝 Contributing

When adding new algorithms to the codebase:

1. **Document the algorithm** using the [template](docs/algorithms/README.md)
2. **Include Mermaid diagrams** for visualization
3. **Add complexity analysis** (time and space)
4. **Provide examples** and edge cases

See [docs/README.md](docs/README.md) for detailed guidelines.

---

**Need help with the documentation?** Check the [documentation guide](docs/README.md) or view the [complete example](docs/algorithms/TileSpawning.md).
