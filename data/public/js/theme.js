function darkMode() {
    document.body.setAttribute("data-color-mode", "dark");
}

function lightMode() {
    document.body.setAttribute("data-color-mode", "light");
}

if (
    window.matchMedia &&
    window.matchMedia("(prefers-color-scheme: dark)").matches
) {
    darkMode();
} else {
    lightMode();
}