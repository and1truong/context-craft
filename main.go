package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	
	"gopkg.in/yaml.v3"
)

func main() {
	// Define CLI arguments
	extensionsFlag := flag.String("extensions", "go,yaml", "Comma-separated list of file extensions to include (e.g., go,yaml)")
	flag.Parse()
	
	// Validate arguments
	if flag.NArg() < 1 {
		fmt.Println("Usage: context-builder <directory> --extensions=go,yaml")
		os.Exit(1)
	}
	
	dir := flag.Arg(0)
	extensions := strings.Split(*extensionsFlag, ",")
	
	// Ensure the directory exists
	if _, err := os.Stat(dir); os.IsNotExist(err) {
		fmt.Println("Error: Directory does not exist:", dir)
		os.Exit(1)
	}
	
	fileContents := make(map[string]string)
	
	// Walk through directory
	err := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		// Skip directories
		if info.IsDir() {
			return nil
		}
		// Check if the file has a valid extension
		ext := strings.TrimPrefix(filepath.Ext(info.Name()), ".")
		if contains(extensions, ext) {
			relPath, err := filepath.Rel(dir, path)
			if err != nil {
				return err
			}
			content, err := os.ReadFile(path)
			if err != nil {
				return err
			}
			fileContents[relPath] = string(content)
		}
		return nil
	})
	
	if err != nil {
		fmt.Println("Error walking directory:", err)
		os.Exit(1)
	}
	
	// Prepare YAML output
	output := map[string]interface{}{
		"context":      fileContents,
		"instructions": []string{"TODO"},
	}
	
	yamlOutput, err := yaml.Marshal(output)
	if err != nil {
		fmt.Println("Error marshaling YAML:", err)
		os.Exit(1)
	}
	
	fmt.Println(string(yamlOutput))
}

// Helper function to check if a slice contains a string
func contains(slice []string, item string) bool {
	for _, s := range slice {
		if s == item {
			return true
		}
	}
	return false
}
