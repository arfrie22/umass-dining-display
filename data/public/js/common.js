const flash_error_icon = '<svg class="octicon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M4.47.22A.75.75 0 015 0h6a.75.75 0 01.53.22l4.25 4.25c.141.14.22.331.22.53v6a.75.75 0 01-.22.53l-4.25 4.25A.75.75 0 0111 16H5a.75.75 0 01-.53-.22L.22 11.53A.75.75 0 010 11V5a.75.75 0 01.22-.53L4.47.22zm.84 1.28L1.5 5.31v5.38l3.81 3.81h5.38l3.81-3.81V5.31L10.69 1.5H5.31zM8 4a.75.75 0 01.75.75v3.5a.75.75 0 01-1.5 0v-3.5A.75.75 0 018 4zm0 8a1 1 0 100-2 1 1 0 000 2z"></path></svg>';
const flash_warn_icon = '<svg class="octicon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M8.22 1.754a.25.25 0 00-.44 0L1.698 13.132a.25.25 0 00.22.368h12.164a.25.25 0 00.22-.368L8.22 1.754zm-1.763-.707c.659-1.234 2.427-1.234 3.086 0l6.082 11.378A1.75 1.75 0 0114.082 15H1.918a1.75 1.75 0 01-1.543-2.575L6.457 1.047zM9 11a1 1 0 11-2 0 1 1 0 012 0zm-.25-5.25a.75.75 0 00-1.5 0v2.5a.75.75 0 001.5 0v-2.5z"></path></svg>';
const flash_success_icon = '<svg class="octicon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path></svg>';
const flash_default_icon = '<svg class="octicon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16" width="16" height="16"><path fill-rule="evenodd" d="M8 1.5a6.5 6.5 0 100 13 6.5 6.5 0 000-13zM0 8a8 8 0 1116 0A8 8 0 010 8zm6.5-.25A.75.75 0 017.25 7h1a.75.75 0 01.75.75v2.75h.25a.75.75 0 010 1.5h-2a.75.75 0 010-1.5h.25v-2h-.25a.75.75 0 01-.75-.75zM8 6a1 1 0 100-2 1 1 0 000 2z"></path></svg>';

function clearValidation(id) {
    document.getElementById(id + "-group").className = "form-group";
    document.getElementById(id + "-validation").className = "note d-none";
    document.getElementById(id + "-validation").innerHTML = "";
}

function errorValidation(id, message) {
    document.getElementById(id + "-group").className = "form-group errored";
    document.getElementById(id + "-validation").className = "note error";
    document.getElementById(id + "-validation").innerHTML = message;
}

function warnValidation(id, message) {
    document.getElementById(id + "-group").className = "form-group warn";
    document.getElementById(id + "-validation").className = "note warning";
    document.getElementById(id + "-validation").innerHTML = message;
}

function successValidation(id, message) {
    document.getElementById(id + "-group").className = "form-group successed";
    document.getElementById(id + "-validation").className = "note success";
    document.getElementById(id + "-validation").innerHTML = message;
}

function flash(status, message) {
    fadein = false;
    if (document.getElementById("flash").classList.contains("fade-out")) {
        fadein = true;
    }

    switch (status) {
        case "error":
            document.getElementById("flash").className = "flash mt-3 flash-error";
            document.getElementById("flash-icon").innerHTML = flash_error_icon;
            break;
        case "warn":
            document.getElementById("flash").className = "flash mt-3 flash-warn";
            document.getElementById("flash-icon").innerHTML = flash_warn_icon;
            break;
        case "success":
            document.getElementById("flash").className = "flash mt-3 flash-success";
            document.getElementById("flash-icon").innerHTML = flash_success_icon;
            break;
        default:
            document.getElementById("flash").className = "flash mt-3";
            document.getElementById("flash-icon").innerHTML = flash_default_icon;
            break;
    }

    if (fadein) {
        document.getElementById("flash").classList.add("fade-in");
    }

    document.getElementById("flash-text").innerHTML = message;
    setTimeout(hideFlash, 5000);
}

function hideFlash() {
    document.getElementById("flash").classList.add("fade-out");

    document.getElementById("flash").addEventListener("animationend", () => {
        document.getElementById("flash").className = "flash mt-3 d-none fade-out";
        document.getElementById("flash-icon").innerHTML = flash_default_icon;
        document.getElementById("flash-text").innerHTML = "";
    }, { once: true });
}