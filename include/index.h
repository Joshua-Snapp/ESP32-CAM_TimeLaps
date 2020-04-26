R"(<!doctype html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width,initial-scale=1">
	<title>ESP32 OV2460 Time-Lapse</title>
	<style>
		body {
			font-family: Arial, Helvetica, sans-serif;
			background: #181818;
			color: #EFEFEF;
			font-size: 16px
		}
		h2 {
			font-size: 18px
		}
		section.main {
			display: flex
		}
		#menu,
		section.main {
			flex-direction: column
		}
		#menu {
			display: none;
			flex-wrap: nowrap;
			min-width: 340px;
			background: #363636;
			padding: 8px;
			border-radius: 4px;
			margin-top: -10px;
			margin-right: 10px;
		}
		#content {
			display: flex;
			flex-wrap: wrap;
			align-items: stretch
		}
		figure {
			padding: 0px;
			margin: 0;
			-webkit-margin-before: 0;
			margin-block-start: 0;
			-webkit-margin-after: 0;
			margin-block-end: 0;
			-webkit-margin-start: 0;
			margin-inline-start: 0;
			-webkit-margin-end: 0;
			margin-inline-end: 0
		}
		figure img {
			display: block;
			width: 100%;
			height: auto;
			border-radius: 4px;
			margin-top: 8px;
		}
		@media (min-width: 800px) and (orientation:landscape) {
			#content {
				display: flex;
				flex-wrap: nowrap;
				align-items: stretch
			}
			figure img {
				display: block;
				max-width: 100%;
				max-height: calc(100vh - 40px);
				width: auto;
				height: auto
			}
			figure {
				padding: 0 0 0 0px;
				margin: 0;
				-webkit-margin-before: 0;
				margin-block-start: 0;
				-webkit-margin-after: 0;
				margin-block-end: 0;
				-webkit-margin-start: 0;
				margin-inline-start: 0;
				-webkit-margin-end: 0;
				margin-inline-end: 0
			}
		}
		section#buttons {
			display: flex;
			flex-wrap: nowrap;
			justify-content: space-between
		}
		#nav-toggle {
			cursor: pointer;
			display: block
		}
		#nav-toggle-cb-ov {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-ov:checked+#menu {
			display: flex
		}
		#nav-toggle-cb-wifi {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-wifi:checked+#menu {
			display: flex
		}
		#nav-toggle-cb-timelaps {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-timelaps:checked+#menu {
			display: flex
		}
		#nav-toggle-cb-cmd {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-cmd:checked+#menu {
			display: flex
		}
		#nav-toggle-cb-mem {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-mem:checked+#menu {
			display: flex
		}
		#nav-toggle-cb-rst {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		#nav-toggle-cb-rst:checked+#menu {
			display: flex
		}
		.input-group {
			display: flex;
			flex-wrap: nowrap;
			line-height: 22px;
			margin: 5px 0
		}
		.input-group>label {
			display: inline-block;
			padding-right: 10px;
			min-width: 47%
		}
		.input-group input,
		.input-group select {
			flex-grow: 1
		}
		.range-max,
		.range-min {
			display: inline-block;
			padding: 0 5px
		}
		button {
			display: block;
			margin: 5px;
			padding: 0 12px;
			border: 0;
			line-height: 28px;
			cursor: pointer;
			color: #fff;
			background: #ff3034;
			border-radius: 5px;
			font-size: 16px;
			outline: 0
		}
		button:hover {
			background: #ff494d
		}
		button:active {
			background: #f21c21
		}
		button.disabled {
			cursor: default;
			background: #a0a0a0
		}
		input[type=range] {
			-webkit-appearance: none;
			width: 100%;
			height: 22px;
			background: #363636;
			cursor: pointer;
			margin: 0
		}
		input[type=range]:focus {
			outline: 0
		}
		input[type=range]::-webkit-slider-runnable-track {
			width: 100%;
			height: 2px;
			cursor: pointer;
			background: #EFEFEF;
			border-radius: 0;
			border: 0 solid #EFEFEF
		}
		input[type=range]::-webkit-slider-thumb {
			border: 1px solid rgba(0, 0, 30, 0);
			height: 22px;
			width: 22px;
			border-radius: 50px;
			background: #ff3034;
			cursor: pointer;
			-webkit-appearance: none;
			margin-top: -11.5px
		}
		input[type=range]:focus::-webkit-slider-runnable-track {
			background: #EFEFEF
		}
		input[type=range]::-moz-range-track {
			width: 100%;
			height: 2px;
			cursor: pointer;
			background: #EFEFEF;
			border-radius: 0;
			border: 0 solid #EFEFEF
		}
		input[type=range]::-moz-range-thumb {
			border: 1px solid rgba(0, 0, 30, 0);
			height: 22px;
			width: 22px;
			border-radius: 50px;
			background: #ff3034;
			cursor: pointer
		}
		input[type=range]::-ms-track {
			width: 100%;
			height: 2px;
			cursor: pointer;
			background: 0 0;
			border-color: transparent;
			color: transparent
		}
		input[type=range]::-ms-fill-lower {
			background: #EFEFEF;
			border: 0 solid #EFEFEF;
			border-radius: 0
		}
		input[type=range]::-ms-fill-upper {
			background: #EFEFEF;
			border: 0 solid #EFEFEF;
			border-radius: 0
		}
		input[type=range]::-ms-thumb {
			border: 1px solid rgba(0, 0, 30, 0);
			height: 22px;
			width: 22px;
			border-radius: 50px;
			background: #ff3034;
			cursor: pointer;
			height: 2px
		}
		input[type=range]:focus::-ms-fill-lower {
			background: #EFEFEF
		}
		input[type=range]:focus::-ms-fill-upper {
			background: #363636
		}
		.switch {
			display: block;
			position: relative;
			line-height: 22px;
			font-size: 16px;
			height: 22px
		}
		.switch input {
			outline: 0;
			opacity: 0;
			width: 0;
			height: 0
		}
		.slider {
			width: 50px;
			height: 22px;
			border-radius: 22px;
			cursor: pointer;
			background-color: grey
		}
		.slider,
		.slider:before {
			display: inline-block;
			transition: .4s
		}
		.slider:before {
			position: relative;
			content: "";
			border-radius: 50%;
			height: 16px;
			width: 16px;
			left: 4px;
			top: 3px;
			background-color: #fff
		}
		input:checked+.slider {
			background-color: #ff3034
		}
		input:checked+.slider:before {
			-webkit-transform: translateX(26px);
			transform: translateX(26px)
		}
		select {
			border: 1px solid #363636;
			font-size: 14px;
			height: 22px;
			outline: 0;
			border-radius: 5px
		}
		.image-container {
			position: relative;
			min-width: 160px
		}
		.close {
			position: absolute;
			right: 5px;
			top: 5px;
			background: #ff3034;
			width: 16px;
			height: 16px;
			border-radius: 100px;
			color: #fff;
			text-align: center;
			line-height: 18px;
			cursor: pointer
		}
		.hidden {
			display: none
		}
	</style>
</head>
<body>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-cmd" id="nav-toggle">&#9776;&nbsp;&nbsp;Commands & Preview</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-cmd" checked="checked">
				<nav id="menu">
					<section id="buttons">
						<button id="get-still">Get Still</button>
						<button id="toggle-stream">Start Stream</button>
					</section>
					<section id="buttons">
						<button id="get-still-save">Get Still & Save</button>
						<button id="toggle-lapse">Start Time-Lapse</button>
					</section>
				</nav>
			</div>
		</div>
		<figure>
			<div id="stream-container" class="image-container hidden">
				<div class="close" id="close-stream">×</div>
				<img id="stream" src="">
			</div>
		</figure>
	</section>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-ov" id="nav-toggle">&#9776;&nbsp;&nbsp;OV2640</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-ov" checked="unchecked">
				<nav id="menu">
					<div class="input-group" id="framesize-group">
						<label for="framesize">Resolution</label>
						<select id="framesize" class="default-action">
							<option value="10">UXGA(1600x1200)</option>
							<option value="9">SXGA(1280x1024)</option>
							<option value="8">XGA(1024x768)</option>
							<option value="7">SVGA(800x600)</option>
							<option value="6">VGA(640x480)</option>
							<option value="5" selected="selected">CIF(400x296)</option>
							<option value="4">QVGA(320x240)</option>
							<option value="3">HQVGA(240x176)</option>
							<option value="0">QQVGA(160x120)</option>
						</select>
					</div>
					<div class="input-group" id="quality-group">
						<label for="quality">Quality</label>
						<div class="range-min">0</div>
						<input type="range" id="quality" min="0" max="63" value="10" class="default-action">
						<div class="range-max">63</div>
					</div>
					<div class="input-group" id="brightness-group">
						<label for="brightness">Brightness</label>
						<div class="range-min">-2</div>
						<input type="range" id="brightness" min="-2" max="2" value="0" class="default-action">
						<div class="range-max">2</div>
					</div>
					<div class="input-group" id="contrast-group">
						<label for="contrast">Contrast</label>
						<div class="range-min">-2</div>
						<input type="range" id="contrast" min="-2" max="2" value="0" class="default-action">
						<div class="range-max">2</div>
					</div>
					<div class="input-group" id="saturation-group">
						<label for="saturation">Saturation</label>
						<div class="range-min">-2</div>
						<input type="range" id="saturation" min="-2" max="2" value="0" class="default-action">
						<div class="range-max">2</div>
					</div>
					<div class="input-group" id="special_effect-group">
						<label for="special_effect">Special Effect</label>
						<select id="special_effect" class="default-action">
							<option value="0" selected="selected">No Effect</option>
							<option value="1">Negative</option>
							<option value="2">Grayscale</option>
							<option value="3">Red Tint</option>
							<option value="4">Green Tint</option>
							<option value="5">Blue Tint</option>
							<option value="6">Sepia</option>
						</select>
					</div>
					<div class="input-group" id="awb_gain-group">
						<label for="awb_gain">AWB Gain</label>
						<div class="switch">
							<input id="awb_gain" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="awb_gain"></label>
						</div>
					</div>
					<div class="input-group" id="wb_mode-group">
						<label for="wb_mode">White Balance</label>
						<select id="wb_mode" class="default-action">
							<option value="0" selected="selected">Auto</option>
							<option value="1">Sunny</option>
							<option value="2">Cloudy</option>
							<option value="3">Office</option>
							<option value="4">Home</option>
						</select>
					</div>
					<div class="input-group" id="aec-group">
						<label for="aec">AEC SENSOR</label>
						<div class="switch">
							<input id="aec" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="aec"></label>
						</div>
					</div>
					<div class="input-group" id="aec2-group">
						<label for="aec2">AEC DSP</label>
						<div class="switch">
							<input id="aec2" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="aec2"></label>
						</div>
					</div>
					<div class="input-group" id="ae_level-group">
						<label for="ae_level">AE Level</label>
						<div class="range-min">-2</div>
						<input type="range" id="ae_level" min="-2" max="2" value="0" class="default-action">
						<div class="range-max">2</div>
					</div>
					<div class="input-group" id="aec_value-group">
						<label for="aec_value">Exposure</label>
						<div class="range-min">0</div>
						<input type="number" id="aec_value" min="0" max="1200" value="204" step="10" class="default-action">
						<div class="range-max">1200</div>
					</div>
					<div class="input-group" id="agc-group">
						<label for="agc">AGC</label>
						<div class="switch">
							<input id="agc" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="agc"></label>
						</div>
					</div>
					<div class="input-group hidden" id="agc_gain-group">
						<label for="agc_gain">Gain</label>
						<div class="range-min">1x</div>
						<input type="range" id="agc_gain" min="0" max="30" value="5" class="default-action">
						<div class="range-max">31x</div>
					</div>
					<div class="input-group" id="gainceiling-group">
						<label for="gainceiling">Gain Ceiling</label>
						<div class="range-min">2x</div>
						<input type="range" id="gainceiling" min="0" max="6" value="0" class="default-action">
						<div class="range-max">128x</div>
					</div>
					<div class="input-group" id="bpc-group">
						<label for="bpc">BPC</label>
						<div class="switch">
							<input id="bpc" type="checkbox" class="default-action">
							<label class="slider" for="bpc"></label>
						</div>
					</div>
					<div class="input-group" id="wpc-group">
						<label for="wpc">WPC</label>
						<div class="switch">
							<input id="wpc" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="wpc"></label>
						</div>
					</div>
					<div class="input-group" id="raw_gma-group">
						<label for="raw_gma">Raw GMA</label>
						<div class="switch">
							<input id="raw_gma" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="raw_gma"></label>
						</div>
					</div>
					<div class="input-group" id="lenc-group">
						<label for="lenc">Lens Correction</label>
						<div class="switch">
							<input id="lenc" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="lenc"></label>
						</div>
					</div>
					<div class="input-group" id="hmirror-group">
						<label for="hmirror">H-Mirror</label>
						<div class="switch">
							<input id="hmirror" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="hmirror"></label>
						</div>
					</div>
					<div class="input-group" id="vflip-group">
						<label for="vflip">V-Flip</label>
						<div class="switch">
							<input id="vflip" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="vflip"></label>
						</div>
					</div>
					<div class="input-group" id="dcw-group">
						<label for="dcw">DCW (Downsize EN)</label>
						<div class="switch">
							<input id="dcw" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="dcw"></label>
						</div>
					</div>
					<section id="buttons">
						<button id="savecfg1">Save 1</button>
						<button id="savecfg2">Save 2</button>
						<button id="savecfg3">Save 3</button>
					</section>
					<section id="buttons">
						<button id="loadcfg1">Load 1</button>
						<button id="loadcfg2">Load 2</button>
						<button id="loadcfg3">Load 3</button>
					</section>
					<section id="buttons">
						<button id="loadcfgdefault">LOAD DEFAULTS</button>
					</section>
				</nav>
			</div>
		</div>
	</section>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-timelaps" id="nav-toggle">&#9776;&nbsp;&nbsp;TimeLaps</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-timelaps" checked="checked">
				<nav id="menu">
					<div class="input-group" id="autostartcfg-group">
						<label for="autostartcfg">Autostart Settings</label>
						<select id="autostartcfg" class="default-action">
							<option value="3">Settings 3</option>
							<option value="2">Settings 2</option>
							<option value="1">Settings 1</option>
							<option value="0" selected="selected">Default Settings</option>
						</select>
					</div>
					<div class="input-group" id="autostart-group">
						<label for="autostart">AutoStart at power on</label>
						<div class="switch">
							<input id="autostart" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="autostart"></label>
						</div>
					</div>
					<div class="input-group" id="interval-group">
						<label for="interval">Time-Lapse Interval [ms]</label>
						<input type="number" id="interval" min="0" max="1000000000" value="1000" step="1000" class="default-action">
					</div>
				</nav>
			</div>
		</div>
	</section>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-wifi" id="nav-toggle">&#9776;&nbsp;&nbsp;WiFi</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-wifi" checked="checked">
				<nav id="menu">
					<div class="input-group" id="WiFiAPOnly-group">
						<label for="WiFiAPOnly">WiFi-AP Only</label>
						<div class="switch">
							<input id="WiFiAPOnly" type="checkbox" class="default-action" checked="checked">
							<label class="slider" for="WiFiAPOnly"></label>
						</div>
					</div>
					<div class="input-group" id="WiFiAPSSID-group">
						<label for="WiFiAPSSID">WiFi AP SSID</label>
						<input type="label" id="WiFiAPSSID" value="undefined" class="default-action">
					</div>
					<div class="input-group" id="WiFiAPPW-group">
						<label for="WiFiAPPW">WiFi AP PW</label>
						<input type="text" id="WiFiAPPW" value="undefined" class="default-action">
					</div>
					<div class="input-group" id="WiFiSSID-group">
						<label for="WiFiSSID">WiFi SSID</label>
						<input type="text" id="WiFiSSID" value="undefined" class="default-action">
					</div>
					<div class="input-group" id="WiFiPW-group">
						<label for="WiFiPW">WiFi PW</label>
						<input type="text" id="WiFiPW" value="undefined" class="default-action">
					</div>
					<section id="buttons">
						<button id="WiFiStop">Turn Off Wifi until reboot</button>
					</section>
				</nav>
			</div>
		</div>
	</section>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-mem" id="nav-toggle">&#9776;&nbsp;&nbsp;Memory</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-mem" checked="checked">
				<nav id="menu">
					<label id="SdCardType" class="default-action">N/A</label>
					<label id="SdCardSize" class="default-action">N/A</label>
					<label id="SdCardTotalSpace" class="default-action">N/A</label>
					<label id="SdCardUsedSpace" class="default-action">N/A</label>
					<label id="SdCardFreeSpace" class="default-action">N/A</label>
					<label id="EepromUsage" class="default-action">N/A</label>
					<label id="FreeHeap" class="default-action">N/A</label>
					<section id="buttons">
						<button id="SdCardInit">Init. SD</button>
						<button id="refreshInfo">Refresh</button>
						<button id="EepromRestoreToDefault">Erase EEPROM</button>
					</section>
				</nav>
			</div>
		</div>
	</section>
	<section class="main">
		<div id="logo">
			<label for="nav-toggle-cb-rst" id="nav-toggle">&#9776;&nbsp;&nbsp;Reset ESP32-CAM</label>
		</div>
		<div id="content">
			<div id="sidebar">
				<input type="checkbox" id="nav-toggle-cb-rst" checked="checked">
				<nav id="menu">
					<section id="buttons">
						<button id="ESPreset">SoftWare Reset ESP32-CAM</button>
					</section>
				</nav>
			</div>
		</div>
	</section>
	<script>
		document.addEventListener('DOMContentLoaded', function (event) {
			var baseHost = document.location.origin
			var streamUrl = baseHost + ':81'
			const hide = el => {
				el.classList.add('hidden')
			}
			const show = el => {
				el.classList.remove('hidden')
			}
			const disable = el => {
				el.classList.add('disabled')
				el.disabled = true
			}
			const enable = el => {
				el.classList.remove('disabled')
				el.disabled = false
			}
			const updateValue = (el, value, updateRemote) => {
				updateRemote = updateRemote == null ? true : updateRemote
				let initialValue
				if (el.type === 'checkbox') {
					initialValue = el.checked
					value = !!value
					el.checked = value
				} else if (el.localName === 'label') {					
					el.innerHTML = value
					initialValue = el.innerHTML
				} else {
					initialValue = el.value
					el.value = value
				}
				if (updateRemote && initialValue !== value) {
					updateConfig(el);
				} else if (!updateRemote) {
					if (el.id === "aec") {
						value ? hide(exposure) : show(exposure)
					} else if (el.id === "agc") {
						if (value) {
							show(gainCeiling)
							hide(agcGain)
						} else {
							hide(gainCeiling)
							show(agcGain)
						}
					} else if (el.id === "awb_gain") {
						value ? show(wb) : hide(wb)
					}
				}
			}
			function ButtonCtrol(command) {
				const query = `${baseHost}/control?var=ButtonCtrl&val=${command}`
				fetch(query)
					.then(response => {
						console.log(`request to ${query} finished, status: ${response.status}`)
					})
				fetch(`${baseHost}/status`)
					.then(function (response) {
						console.log(response)
						return response.json()
					})
					.then(function (state) {
						console.log(state)
						document
							.querySelectorAll('.default-action')
							.forEach(el => {
								updateValue(el, state[el.id], false)
							})
					})
			}
			function updateConfig(el) {
				let value
				switch (el.type) {
					case 'checkbox':
						value = el.checked ? 1 : 0
						break
					case 'range':
						value = el.value
						break
					case 'select-one':
						value = el.value
						break
					case 'number':
						value = el.value
						break
					case 'text':
						value = el.value
						break
					default:
						return
				}
				const query = `${baseHost}/control?var=${el.id}&val=${value}`
				fetch(query)
					.then(response => {
						console.log(`request to ${query} finished, status: ${response.status}`)
					})
			}
			document
				.querySelectorAll('.close')
				.forEach(el => {
					el.onclick = () => {
						hide(el.parentNode)
					}
				})
			// read initial values
			fetch(`${baseHost}/status`)
				.then(function (response) {
					console.log(response)
					return response.json()
				})
				.then(function (state) {
					console.log(state)
					document
						.querySelectorAll('.default-action')
						.forEach(el => {
							updateValue(el, state[el.id], false)
						})
				})
			const view = document.getElementById('stream')
			const viewContainer = document.getElementById('stream-container')
			const stillButton = document.getElementById('get-still')
			const stillSaveButton = document.getElementById('get-still-save')
			const streamButton = document.getElementById('toggle-stream')
			const lapseButton = document.getElementById('toggle-lapse')
			const closeButton = document.getElementById('close-stream')
			const resetButton = document.getElementById('ESPreset')
			const saveCfg1Button = document.getElementById('savecfg1')
			const saveCfg2Button = document.getElementById('savecfg2')
			const saveCfg3Button = document.getElementById('savecfg3')
			const loadCfg1Button = document.getElementById('loadcfg1')
			const loadCfg2Button = document.getElementById('loadcfg2')
			const loadCfg3Button = document.getElementById('loadcfg3')
			const loadCfg0Button = document.getElementById('loadcfgdefault')
			const wifiStopButton = document.getElementById('WiFiStop')
			const InitSDButton = document.getElementById('SdCardInit')
			const RefreshPageButton = document.getElementById('refreshInfo')
			const restoreEepromToDefaultButton = document.getElementById('EepromRestoreToDefault')
			const stopStream = () => {
				window.stop();
				streamButton.innerHTML = 'Start Stream'
			}
			const startStream = () => {
				view.src = `${streamUrl}/stream`
				show(viewContainer)
				streamButton.innerHTML = 'Stop Stream'
			}
			// Attach actions to buttons
			stillButton.onclick = () => {
				stopStream()
				view.src = `${baseHost}/capture?_cb=${Date.now()}`
				show(viewContainer)
			}
			stillSaveButton.onclick = () => {
				stopStream()
				view.src = `${baseHost}/capture_save?_cb=${Date.now()}`
				show(viewContainer)
			}			
			closeButton.onclick = () => {
				stopStream()
				hide(viewContainer)
			}
			streamButton.onclick = () => {
				const streamEnabled = streamButton.innerHTML === 'Stop Stream'
				if (streamEnabled) {
					stopStream()
				} else {
					startStream()
				}
			}
			lapseButton.onclick = () => {
				const lapseEnabled = lapseButton.innerHTML === 'Stop Time-Lapse'
				if (lapseEnabled) {
					lapseButton.innerHTML = 'Start Time-Lapse'
				} else {
					lapseButton.innerHTML = 'Stop Time-Lapse'
				}
				ButtonCtrol(lapseButton.id + lapseEnabled)
			}
			wifiStopButton.onclick = () => {
				ButtonCtrol(wifiStopButton.id)
			}
			resetButton.onclick = () => {
				ButtonCtrol(resetButton.id)
			}
			saveCfg1Button.onclick = () => {
				ButtonCtrol(saveCfg1Button.id)
			}
			saveCfg2Button.onclick = () => {
				ButtonCtrol(saveCfg2Button.id)
			}
			saveCfg3Button.onclick = () => {
				ButtonCtrol(saveCfg3Button.id)
			}
			loadCfg1Button.onclick = () => {
				ButtonCtrol(loadCfg1Button.id)
			}
			loadCfg2Button.onclick = () => {
				ButtonCtrol(loadCfg2Button.id)
			}
			loadCfg3Button.onclick = () => {
				ButtonCtrol(loadCfg3Button.id)
			}
			loadCfg0Button.onclick = () => {
				ButtonCtrol(loadCfg0Button.id)
			}
			InitSDButton.onclick = () => {
				ButtonCtrol(InitSDButton.id)
			}
			RefreshPageButton.onclick = () => {
				ButtonCtrol(RefreshPageButton.id)
			}
			restoreEepromToDefaultButton.onclick = () => {
				ButtonCtrol(restoreEepromToDefaultButton.id)
			}
			// Attach default on change action
			document
				.querySelectorAll('.default-action')
				.forEach(el => {
					el.onchange = () => updateConfig(el)
				})
			// Custom actions
			// Gain
			const agc = document.getElementById('agc')
			const agcGain = document.getElementById('agc_gain-group')
			const gainCeiling = document.getElementById('gainceiling-group')
			agc.onchange = () => {
				updateConfig(agc)
				if (agc.checked) {
					show(gainCeiling)
					hide(agcGain)
				} else {
					hide(gainCeiling)
					show(agcGain)
				}
			}
			// Exposure
			const aec = document.getElementById('aec')
			const exposure = document.getElementById('aec_value-group')
			aec.onchange = () => {
				updateConfig(aec)
				aec.checked ? hide(exposure) : show(exposure)
			}
			// AWB
			const awb = document.getElementById('awb_gain')
			const wb = document.getElementById('wb_mode-group')
			awb.onchange = () => {
				updateConfig(awb)
				awb.checked ? show(wb) : hide(wb)
			}
		})
	</script>
</body>
</html>
)"