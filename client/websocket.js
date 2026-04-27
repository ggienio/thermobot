const speed = 0.5;
const commands = {
    'btn-forward': { cmd: 'MOVE', vx: 0, vy: speed, omega: 0 },
    'btn-backward': { cmd: 'MOVE', vx: 0, vy: -speed, omega: 0 },
    'btn-left': { cmd: 'MOVE', vx: -speed, vy: 0, omega: 0 },
    'btn-right': { cmd: 'MOVE', vx: speed, vy: 0, omega: 0 },
    'btn-topleft': { cmd: 'MOVE', vx: -speed, vy: speed, omega: 0 },
    'btn-topright': { cmd: 'MOVE', vx: speed, vy: speed, omega: 0 },
    'btn-bottomleft': { cmd: 'MOVE', vx: -speed, vy: -speed, omega: 0 },
    'btn-bottomright': { cmd: 'MOVE', vx: speed, vy: -speed, omega: 0 },
    'btn-rotateleft': { cmd: 'MOVE', vx: 0, vy: 0, omega: -speed },
    'btn-rotateright': { cmd: 'MOVE', vx: 0, vy: 0, omega: speed },
    'btn-stop': { cmd: 'MOVE', vx: 0, vy: 0, omega: 0 }
};

const ws = new WebSocket('ws://192.168.4.1:82/ws');

ws.onopen = () => {
    console.log('Connected to server');
    document.getElementById('status-circle').classList.add('connected');
    document.getElementById('status-circle').classList.remove('disconnected');
    document.getElementById('status-text').innerHTML = "connected";
};

ws.onerror = (error) => {
    console.error('WebSocket error:', error);
};

ws.onclose = () => {
    console.log('Connection closed');
    document.getElementById('status-circle').classList.remove('connected');
    document.getElementById('status-circle').classList.add('disconnected');
    document.getElementById('status-text').innerHTML = "disconnected";
};

const INTERVAL_MS = 250;

function sendCommand(command) {
    if (ws.readyState === WebSocket.OPEN) {
        ws.send(JSON.stringify(command));
    }
    console.log("Sent command:", command);
}

let activeInterval = null;

function clearMove() {
    if (activeInterval !== null) {
        clearInterval(activeInterval);
        activeInterval = null;
    }
}

function startMove(command) {
    clearMove();
    sendCommand(command);
    activeInterval = setInterval(() => sendCommand(command), INTERVAL_MS);
}

function stopMove() {
    clearMove();
    sendCommand(commands['btn-stop']);
}

document.querySelectorAll('.arrow-pad button:not(.empty)').forEach(button => {
    const command = commands[button.className];

    button.addEventListener('mousedown',  (e) => { e.preventDefault(); startMove(command); });
    button.addEventListener('touchstart', (e) => { e.preventDefault(); startMove(command); });

    // Also stop if cursor leaves while held
    button.addEventListener('mouseleave', () => {
        if (activeInterval !== null) stopMove();
    });
});

document.addEventListener('mouseup',    stopMove);
document.addEventListener('touchend',   stopMove);
document.addEventListener('touchcancel', stopMove);

// Keyboard support
const keyMap = {
    'w': { vx: 0,      vy: speed  },
    's': { vx: 0,      vy: -speed },
    'a': { vx: -speed, vy: 0      },
    'd': { vx: speed,  vy: 0      },
    'q': { omega: -speed },
    'e': { omega: speed  },
};

const heldKeys = new Set();

function getKeyboardCommand() {
    let vx = 0, vy = 0, omega = 0;
    for (const key of heldKeys) {
        const k = keyMap[key];
        if (!k) continue;
        vx    += k.vx    ?? 0;
        vy    += k.vy    ?? 0;
        omega += k.omega ?? 0;
    }
    return { cmd: 'MOVE', vx, vy, omega };
}

function updateKeyboardMove() {
    clearMove();
    if (heldKeys.size === 0) {
        sendCommand(commands['btn-stop']);
        return;
    }
    const command = getKeyboardCommand();
    sendCommand(command);
    activeInterval = setInterval(() => sendCommand(getKeyboardCommand()), INTERVAL_MS);
}

document.addEventListener('keydown', (e) => {
    if (e.repeat) return;
    if (e.key === ' ') { heldKeys.clear(); updateKeyboardMove(); return; }
    const key = e.key.toLowerCase();
    if (!keyMap[key]) return;
    heldKeys.add(key);
    updateKeyboardMove();
});

document.addEventListener('keyup', (e) => {
    const key = e.key.toLowerCase();
    heldKeys.delete(key);
    updateKeyboardMove();
});