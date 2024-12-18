import DeviceSetting from "./component/DeviceSetting/DeviceSetting"
import ListCodeButton from "./component/ListCodeButton/ListCodeButton"
import ScanDevice from "./component/ScanDevice/ScanDevice"

function App() {
  return (
    <div className="container">
      <ScanDevice className="scan-device" />
      <DeviceSetting className="device-setting" />
      <ListCodeButton className="list-code-button" />
    </div>
  )
}

export default App
