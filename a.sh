alias build='mkdir build && (cd build && cmake .. && make)'
alias run='clear && build/examples/binary'
alias clean='rm -r build && clear'
alias mk='(cd build && make)'
alias mkrun='clear && (cd build && make) && build/examples/binary'
echo "Applied Aliases"