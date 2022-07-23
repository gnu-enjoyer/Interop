echo "Main"

proc add3(a: int): int {.importc, dynlib: "./lib/dyn.so".}

echo "Adding three to seven"
echo ($ add3(7))