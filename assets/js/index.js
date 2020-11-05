const profile = `<div class="profile">
<div class="profile-title-wrapper">
  <div class="profile-title">Profile</div>
  <div class="delete-btn-wrapper">
    <div class="delete-btn">Delete</div>
  </div>
</div>
<div class="profile-inner">
  <div class="input-name">Name</div>
  <input class="profile-input-text name" type="text" placeholder="Name">
</div>
<div class="profile-inner">
  <div class="input-name">Signature</div>
  <input class="profile-input-text signature" type="text" placeholder="Signature">
</div>
<div class="profile-inner">
  <div class="input-name">Module</div>
  <input class="profile-input-text module" type="text" placeholder="Module">
</div>
<div class="profile-inner">
  <div class="input-name">Offset</div>
  <input class="profile-input-text num offset" type="text" placeholder="Offset" value="0">
</div>
<div class="profile-inner">
  <div class="input-name">Extra</div>
  <input class="profile-input-text num extra" type="text" placeholder="Extra" value="0">
</div>
<div class="profile-inner">
  <div class="input-name">x64relative</div>
  <input class="profile-input-cb x64relative" type="checkbox">
</div>
</div>`;

var toml = require('@iarna/toml');

$(document).ready(function() {
  $.get("config.toml", function (data) { //Load the file from where app.html is.
    var config = toml.parse(data);
    $(".game-name").val(config.game);
    $(".export-dir").val(config.export_dir);
    for (let i = 0; i < config.profile.length; i++) {
      $(".profile-wrapper").append(profile);
      $(".profile").last().find(".name").val(config.profile[i].name);
      $(".profile").last().find(".signature").val(config.profile[i].signature);
      $(".profile").last().find(".module").val(config.profile[i].module);
      $(".profile").last().find(".offset").val(config.profile[i].offset);
      $(".profile").last().find(".extra").val(config.profile[i].extra);
      $(".profile").last().find(".x64relative").prop("checked", config.profile[i].x64relative);
    }
  });
});

$(".delete-btn").click(function () {
    $(this).parent().parent().parent().remove();
});

$(".add-btn").click(function () {
    $(".profile-wrapper").append(profile);
});

$(document).on("click", ".delete-btn", function(){
    $(this).parent().parent().parent().remove();
});

var fs = require('fs');

function writeFile(path, data) {
  fs.writeFile(path, data, function (err) {
    if (err) {
        throw err;
    }
  });
}

$(".run-btn").click(function () {
  // run MiraDump.exe
  var fileContent = ""; //Further declaration of file content.
  var gameName = $(".game-name").val();
  var exportDir = $(".export-dir").val();
  fileContent += toml.stringify({game: gameName, export_dir: exportDir});

  var nameValue, signatureValue, moduleValue, offsetValue, extraValue, x64relativeValue;

  for (let i = 0; i < $(".profile").length; i++) {
    nameValue = $(".profile").eq(i).find(".name").val();
    signatureValue = $(".profile").eq(i).find(".signature").val();
    moduleValue = $(".profile").eq(i).find(".module").val();
    offsetValue = Number($(".profile").eq(i).find(".offset").val());
    extraValue = Number($(".profile").eq(i).find(".extra").val());
    x64relativeValue = $(".profile").eq(i).find(".x64relative").prop("checked");
    var profileObject = {profile: [{
      name: nameValue,
      signature: signatureValue,
      module: moduleValue,
      offset: offsetValue,
      extra: extraValue,
      x64relative: x64relativeValue
    }]};
    fileContent += toml.stringify(profileObject);
  }

  writeFile("config.toml", fileContent); //Load the file from where main.js is.

  const exec = require('child_process').exec;

  exec("MiraDump", (err,stdout) => {
    $(".output").textWithLF(stdout);
  });
});
