# Speller

This folder contains my solution for the **CS50x Week 5 Speller problem set**.

## Description

The Speller problem required implementing a spell checker that loads a dictionary into memory and checks words from a text file against that dictionary.

## Implementation

The spell checker uses:

* **Hash Table** – for efficient word lookup
* **Linked Lists** – to handle collisions
* **Hash Function** – to determine the appropriate bucket
* **Dynamic Memory Allocation** – to create dictionary nodes
* **Memory Deallocation** – to properly free all allocated memory

## Functions Implemented

* `load()` – Loads dictionary words into memory.
* `check()` – Checks whether a word exists in the dictionary.
* `hash()` – Converts a word into a hash-table index.
* `size()` – Returns the number of words loaded.
* `unload()` – Frees all allocated memory.

## Key Learning

This problem strengthened my understanding of **hash tables, linked lists, pointers, dynamic memory allocation, memory management, and algorithm efficiency**.
