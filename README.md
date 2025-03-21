# ContextCraft (C++ Version)

**ContextCraft** is a lightweight command-line tool, written in C++, designed to generate structured YAML representations of your project's codebase. It captures the context of your working directory, including subdirectories, and outputs it in a format suitable for embedding into AI-driven workflows.  This allows you to easily use large language models (LLMs) to modify, enhance, or add features to your project.

---

## Features

-   **Flexible File Filtering:** Specify file extensions to include (e.g., `.cpp`, `.h`, `.hpp`, `.yaml`).
-   **Directory Traversal:** Automatically includes files from subdirectories.
-   **YAML Output:** Produces a clean, structured YAML format for easy integration with AI tools.
-   **Cross-Platform:** Built using C++17 and `<filesystem>`, ensuring compatibility with Windows, macOS, and Linux.

---

## Installation

1.  **Prerequisites:**
    *   A C++ compiler that supports C++17 (e.g., GCC 8+, Clang 5+, Visual Studio 2017+).
    *   On Linux, you may need to install the development package for `libstdc++` (e.g., `libstdc++-dev` or `libstdc++-devel`).  See the "Troubleshooting" section below for details.

2.  **Clone the repository:**

    ```bash
    git clone git@github.com:and1truong/context-craft.git  # Or your fork
    cd context-craft
    ```

3.  **Build the binary:**

    *   **Linux/macOS (g++):**

        ```bash
        g++ -std=c++17 contextcraft.cpp -o contextcraft -lstdc++fs
        ```
        *Note: On some older Linux systems or with older compilers, `-lstdc++fs` might be required. On modern macOS systems, you can likely omit `-lstdc++fs`.*
        
        If you receive a "library not found" error, please refer to the Troubleshooting section.

    *   **Linux/macOS (clang++):**

        ```bash
        clang++ -std=c++17 contextcraft.cpp -o contextcraft -lstdc++fs
        ```
       *Note: On some older Linux systems or with older compilers, `-lstdc++fs` might be required. On modern macOS systems, you can likely omit `-lstdc++fs`.*

    *   **Windows (Visual Studio):**
        1.  Open the "Developer Command Prompt for VS" for your Visual Studio version.
        2.  Navigate to the `context-craft` directory.
        3.  Compile:

            ```bash
            cl /std:c++17 contextcraft.cpp /EHsc /Fe:contextcraft.exe
            ```

4.  **Move the binary to your PATH (optional):**

    *   **Linux/macOS:**

        ```bash
        sudo mv contextcraft /usr/local/bin/
        ```

    *   **Windows:**  You can add the directory containing `contextcraft.exe` to your system's `PATH` environment variable.  This allows you to run `contextcraft` from any directory in the command prompt.

---

## Usage

### Basic Command

```bash
contextcraft <directory> --extensions=cpp,h,yaml
```

