const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;

let mainWindow = null;

app.on('window-`all-closed', function() {
    app.quit();
});

app.on('ready', function() {
  mainWindow = new BrowserWindow({width: 1100, height: 700, webPreferences:{nodeIntegration: true}});
  mainWindow.loadURL('file://' + __dirname + '/assets/app.html');

  mainWindow.on('closed', function() {
    mainWindow = null;
  });
});
