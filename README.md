## Description 📄
This project is an efficient autocomplete implementation using tries, written in C. RMM provides a fast and reliable way to suggest completions for partial text inputs. To test out the completions, I also plan to add a curses based TUI to go along with it. The projects stands as a look under-the-hood of how these engines work at the fundamental level.

## Overview 👓
RMM implements an autocomplete system using a trie data structure. The trie (prefix tree) enables quick lookup of possible completions for a given input, making text entry and search operations more efficient. Moreover, for a large dataset Tries are more space efficient as well.

## To-Do ✅
- [x] Figure out efficient string handling in C
- [x] Implement the trie interface
- [x] Implement some way to retrieve top 5 predictions
- [x] Optimize for the entire dataset
- [ ] Implement a TUI using ncurses
- [ ] API documentation for easier integration with other programs

## Contributing 🤝
If you feel like you have some contibutions to make to RMM, feel free to do the same. Here are the steps for your aid:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Implement your changes and commit them with clear messages.
4. Push your branch to your forked repository.
5. Open a pull request describing your changes and the problem they solve.

## License 📃
Read-My-Mind is licensed under the MIT License. See [LICENSE](LICENSE) for more information.
