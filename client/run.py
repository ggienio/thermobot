import socketserver
import webbrowser
import threading
import os

import http.server

# Set the port for the server
PORT = 8000

# Change to the directory where the script is located (or specify a static folder)
os.chdir(os.path.dirname(__file__))

# Create a simple HTTP request handler
Handler = http.server.SimpleHTTPRequestHandler

# Function to run the server
def run_server():
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print(f"Serving at http://localhost:{PORT}")
        httpd.serve_forever()

# Start the server in a separate thread
server_thread = threading.Thread(target=run_server, daemon=True)
server_thread.start()

# Open the default web browser to the server URL
webbrowser.open(f"http://localhost:{PORT}")

# Keep the main thread alive
input("Press Enter to stop the server...\n")