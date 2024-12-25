import DeviceSetting from "./component/DeviceSetting/DeviceSetting"
import ListCodeButton from "./component/ListCodeButton/ListCodeButton"
import ScanDevice from "./component/ScanDevice/ScanDevice"
import { SerialProvider } from "./component/SerialContext"

function App() {
  return (
    <SerialProvider>
      <div className="container">
        <ScanDevice className="scan-device" />
        <DeviceSetting className="device-setting" />
        <ListCodeButton className="list-code-button" />
      </div>
    </SerialProvider>
  )
}

export default App
