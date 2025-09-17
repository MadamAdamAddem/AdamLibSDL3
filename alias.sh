alias build='mkdir build && cd build && cmake .. && make && cd ..'
alias run='clear && build/binary'
alias clean='rm -r build && clear'
alias brun='build && run'
echo "Applied Aliases"