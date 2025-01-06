import { SerialContext } from '../SerialContext';
import React, { useContext } from "react";
import './ScanDevice.css'

const ScanDevice = () => {
  const { connectToSerial, receivedData, output } = useContext(SerialContext);
  const data = [
    
  ];
  return (
    <div className="ScanDevice">
      <table className="ScanDevice-table">
        <thead>
          <tr>
            <th>Foot Keyboard</th>
          </tr>
        </thead>
        <tbody>
          {data.map((item, index) => (
            <tr key={index}>
              <td>{item}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default ScanDevice