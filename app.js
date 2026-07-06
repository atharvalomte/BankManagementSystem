const GATEWAY_URL = 'http://localhost:18080/api/bank';

document.addEventListener("DOMContentLoaded", () => {
    const tl = gsap.timeline();

    tl.from(".hero-header .badge", { opacity: 0, y: -20, duration: 0.5, ease: "power3.out" })
      .from(".hero-header h1", { opacity: 0, y: -30, duration: 0.6, ease: "power3.out" }, "-=0.3")
      .from(".hero-header p", { opacity: 0, y: -20, duration: 0.6, ease: "power3.out" }, "-=0.4");

    tl.from(".module-card", {
        opacity: 0,
        y: 40,
        duration: 0.7,
        stagger: 0.15,
        ease: "power4.out"
    }, "-=0.4");

    tl.from(".terminal-shell", { opacity: 0, y: 30, duration: 0.6, ease: "power3.out" }, "-=0.5");
});

function updateTerminalOutput(rawStdout) {
    const stream = document.getElementById('terminalStream');
    let filteredText = rawStdout.replace(/BANK MANAGEMENT SYSTEM[\s\S]*?Choice:/g, '');
    filteredText = filteredText.replace(/Choice:/g, '');
    
    stream.innerText = `> Execution Response Received:\n${filteredText.trim()}\n\n` + stream.innerText;
    
    gsap.fromTo(stream, { color: "#ffffff" }, { color: "#a5f3fc", duration: 0.4 });
}

async function dispatchPayloadToCpp(choiceCode, argsList = []) {
    try {
        const response = await fetch(GATEWAY_URL, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ choice: choiceCode, args: argsList })
        });
        
        const data = await response.json();
        if (data.output) {
            updateTerminalOutput(data.output);
        }
    } catch (error) {
        document.getElementById('terminalStream').innerText = `> Communication Pipeline Interruption: ${error.message}\n` + document.getElementById('terminalStream').innerText;
    }
}

function animateButtonClick(elementId) {
    gsap.fromTo(`#${elementId}`, { scale: 0.96 }, { scale: 1, duration: 0.2, ease: "power2.out" });
}

document.getElementById('creationForm').addEventListener('submit', (e) => {
    e.preventDefault();
    const accNo = document.getElementById('newNumber').value;
    const holder = document.getElementById('newHolder').value;
    const balance = document.getElementById('newBalance').value;
    const type = document.getElementById('newType').value;
    
    dispatchPayloadToCpp(1, [accNo, holder, balance, type]);
    document.getElementById('creationForm').reset();
});

document.getElementById('depositTrigger').addEventListener('click', () => {
    animateButtonClick('depositTrigger');
    const accNo = document.getElementById('targetNumber').value;
    const amount = document.getElementById('ledgerAmount').value;
    if(!accNo || !amount) return alert("Required operational payload values empty.");
    dispatchPayloadToCpp(2, [accNo, amount]);
});

document.getElementById('withdrawTrigger').addEventListener('click', () => {
    animateButtonClick('withdrawTrigger');
    const accNo = document.getElementById('targetNumber').value;
    const amount = document.getElementById('ledgerAmount').value;
    if(!accNo || !amount) return alert("Required operational payload values empty.");
    dispatchPayloadToCpp(3, [accNo, amount]);
});

document.getElementById('inspectTrigger').addEventListener('click', () => {
    animateButtonClick('inspectTrigger');
    const accNo = document.getElementById('adminTargetNumber').value;
    if(!accNo) return alert("Enter target Account ID.");
    dispatchPayloadToCpp(4, [accNo]);
});

document.getElementById('listAllTrigger').addEventListener('click', () => {
    animateButtonClick('listAllTrigger');
    dispatchPayloadToCpp(5);
});

document.getElementById('purgeTrigger').addEventListener('click', () => {
    animateButtonClick('purgeTrigger');
    const accNo = document.getElementById('adminTargetNumber').value;
    if(!accNo) return alert("Enter target Account ID.");
    dispatchPayloadToCpp(6, [accNo]);
    document.getElementById('adminTargetNumber').value = '';
});